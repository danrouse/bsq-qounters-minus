#include "Qounters/NotesQounter.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::Qounters::NotesQounter);

QountersMinus::Qounter* QountersMinus::Qounters::NotesQounter::Initialize() {
    if (!config.NotesQounterConfig.enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::NotesQounter*>(
        config.NotesQounterConfig.position, config.NotesQounterConfig.distance
    );
}

void QountersMinus::Qounters::NotesQounter::Start() {
    CreateBasicTitle("Notes");

    std::string defaultText = "0";
    if (config.NotesQounterConfig.showPercentage) defaultText += " - " + FormatNumber(100.0f, config.NotesQounterConfig.decimalPrecision) + "%";
    CreateBasicText(defaultText);
}

void QountersMinus::Qounters::NotesQounter::UpdateValue() {
    auto text = std::to_string(goodCuts) + "/" + std::to_string(allCuts);
    if (config.NotesQounterConfig.showPercentage) {
        text += " - " + FormatNumber((100.0f * goodCuts) / allCuts, config.NotesQounterConfig.decimalPrecision) + "%";
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
