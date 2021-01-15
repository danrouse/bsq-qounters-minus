#include "Qounters/MissedQounter.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::Qounters::MissedQounter);

QountersMinus::Qounter* QountersMinus::Qounters::MissedQounter::Initialize() {
    if (!config.MissedQounterConfig.enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::MissedQounter*>(
        config.MissedQounterConfig.position, config.MissedQounterConfig.distance
    );
}

void QountersMinus::Qounters::MissedQounter::Start() {
    CreateBasicTitle("Misses");
    CreateBasicText("0");
}

void QountersMinus::Qounters::MissedQounter::UpdateValue() {
    basicText->set_text(il2cpp_utils::createcsstr(std::to_string(misses)));
}

void QountersMinus::Qounters::MissedQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (config.MissedQounterConfig.countBadCuts && !info->get_allIsOK() && data->colorType != GlobalNamespace::ColorType::None) {
        misses++;
        UpdateValue();
    }
}

void QountersMinus::Qounters::MissedQounter::OnNoteMiss(GlobalNamespace::NoteData* data) {
    if (data->colorType != GlobalNamespace::ColorType::None) {
        misses++;
        UpdateValue();
    }
}
