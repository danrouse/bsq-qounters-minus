#include "Qounters/NotesQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::NotesQounter);

bool QountersMinus::Qounters::NotesQounter::Enabled = false;
int QountersMinus::Qounters::NotesQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowCombo);
int QountersMinus::Qounters::NotesQounter::Distance = 1;
bool QountersMinus::Qounters::NotesQounter::ShowPercentage = false;
int QountersMinus::Qounters::NotesQounter::DecimalPrecision = 2;

void QountersMinus::Qounters::NotesQounter::Register() {
    QounterRegistry::Register<NotesQounter>("Note Qounter", "NoteConfig", true);
    QounterRegistry::RegisterConfig<NotesQounter>({
        .ptr = &Enabled,
        .field = "Enabled",
    });
    QounterRegistry::RegisterConfig<NotesQounter>({
        .ptr = &Position,
        .field = "Position",
        .enumNumElements = QounterPositionCount,
        .enumDisplayNames = QounterPositionNames,
        .enumSerializedNames = QounterPositionLookup,
    });
    QounterRegistry::RegisterConfig<NotesQounter>({
        .ptr = &Distance,
        .field = "Distance",
    });
    QounterRegistry::RegisterConfig<NotesQounter>({
        .ptr = &ShowPercentage,
        .field = "ShowPercentage",
        .displayName = "Show Percentage",
        .helpText = "Toggles the percentage of notes hit over total notes.",
    });
    QounterRegistry::RegisterConfig<NotesQounter>({
        .ptr = &DecimalPrecision,
        .field = "DecimalPrecision",
        .displayName = "Percentage Precision",
        .helpText = "How precise should the percentage be?",
        .intMin = 0,
        .intMax = 5,
    });
}

QountersMinus::Qounter* QountersMinus::Qounters::NotesQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::NotesQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
    );
}

void QountersMinus::Qounters::NotesQounter::Start() {
    CreateBasicTitle("Notes");

    std::string defaultText = "0";
    if (ShowPercentage) defaultText += " - " + FormatNumber(100.0f, DecimalPrecision) + "%";
    CreateBasicText(defaultText);
}

void QountersMinus::Qounters::NotesQounter::UpdateValue() {
    auto text = std::to_string(goodCuts) + "/" + std::to_string(allCuts);
    if (ShowPercentage) {
        text += " - " + FormatNumber((100.0f * goodCuts) / allCuts, DecimalPrecision) + "%";
    }
    basicText->set_text(il2cpp_utils::createcsstr(text));
}

void QountersMinus::Qounters::NotesQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    allCuts++;
    if (info->get_allIsOK() && data->colorType != GlobalNamespace::ColorType::None) {
        goodCuts++;
    }
    UpdateValue();
}

void QountersMinus::Qounters::NotesQounter::OnNoteMiss(GlobalNamespace::NoteData* data) {
    if (data->colorType != GlobalNamespace::ColorType::None) {
        allCuts++;
        UpdateValue();
    }
}
