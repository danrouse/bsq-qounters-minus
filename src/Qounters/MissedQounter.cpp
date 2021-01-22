#include "Qounters/MissedQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::MissedQounter);

bool QountersMinus::Qounters::MissedQounter::Enabled = true;
int QountersMinus::Qounters::MissedQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowCombo);
int QountersMinus::Qounters::MissedQounter::Distance = 0;
bool QountersMinus::Qounters::MissedQounter::CountBadCuts = true;

void QountersMinus::Qounters::MissedQounter::Register() {
    QounterRegistry::Register<MissedQounter>("Missed Qounter", "MissedConfig");
    QounterRegistry::RegisterConfig<MissedQounter>({
        .ptr = &Enabled,
        .field = "Enabled",
    });
    QounterRegistry::RegisterConfig<MissedQounter>({
        .ptr = &Position,
        .field = "Position",
        .enumNumElements = QounterPositionCount,
        .enumDisplayNames = QounterPositionNames,
        .enumSerializedNames = QounterPositionLookup,
    });
    QounterRegistry::RegisterConfig<MissedQounter>({
        .ptr = &Distance,
        .field = "Distance",
    });
    QounterRegistry::RegisterConfig<MissedQounter>({
        .ptr = &CountBadCuts,
        .field = "CountBadCuts",
        .displayName = "Include Bad Cuts",
        .helpText = "Bad cuts count towards the Missed counter.",
    });
}

QountersMinus::Qounter* QountersMinus::Qounters::MissedQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::MissedQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
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
    if (CountBadCuts && !info->get_allIsOK() && data->colorType != GlobalNamespace::ColorType::None) {
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
