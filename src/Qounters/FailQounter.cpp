#include "Qounters/FailQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::FailQounter);

bool QountersMinus::Qounters::FailQounter::Enabled = false;
int QountersMinus::Qounters::FailQounter::Position = static_cast<int>(QountersMinus::QounterPosition::AboveCombo);
int QountersMinus::Qounters::FailQounter::Distance = 0;
bool QountersMinus::Qounters::FailQounter::ShowRestartsInstead = true;

int QountersMinus::Qounters::FailQounter::restarts = 0;
Il2CppString* QountersMinus::Qounters::FailQounter::prevBeatmapHash = nullptr;

QountersMinus::Qounter* QountersMinus::Qounters::FailQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::FailQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
    );
}

void QountersMinus::Qounters::FailQounter::Start() {
    CreateBasicTitle(ShowRestartsInstead ? "Restarts" : "Fails");

    auto songID = GetSongID(refs->difficultyBeatmap);
    auto currentBeatmapHash = songID.hash + "_" + std::to_string(songID.difficulty);

    if (ShowRestartsInstead) {
        if (prevBeatmapHash != nullptr && to_utf8(csstrtostr(prevBeatmapHash)) == currentBeatmapHash) {
            restarts++;
            count = restarts;
        } else {
            restarts = count = 0;
            prevBeatmapHash = il2cpp_utils::createcsstr(currentBeatmapHash, il2cpp_utils::StringType::Manual);
        }
    } else {
        count = refs->playerData->playerAllOverallStatsData->get_allOverallStatsData()->failedLevelsCount;
        auto gameEnergyCounter = UnityEngine::Object::FindObjectOfType<GlobalNamespace::GameEnergyCounter*>();
        gameEnergyCounter->add_gameEnergyDidReach0Event(il2cpp_utils::MakeDelegate<System::Action*>(
            classof(System::Action*), this, +[](QountersMinus::Qounters::FailQounter* self) {
                self->count += 1;
                self->basicText->set_text(il2cpp_utils::createcsstr(std::to_string(self->count)));
                self->animationTimer = 0.0f;
            }
        ));
    }

    CreateBasicText(std::to_string(count));
    animationTimer = 10.0f;
}

void QountersMinus::Qounters::FailQounter::Update() {
    if (animationTimer < 1.0f) {
        basicText->set_color(UnityEngine::Color::Lerp(UnityEngine::Color::get_white(), UnityEngine::Color::get_red(), animationTimer));
        animationTimer += UnityEngine::Time::get_deltaTime();
    }
}
