#include "Qounters/NotesQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::NotesQounter);

void QountersMinus::Qounters::NotesQounter::Configure(QountersMinus::NotesQounterConfig config) {
    showPercentage = config.showPercentage;
    decimalPrecision = config.decimalPrecision;

    CreateBasicTitle("Notes");

    std::string defaultText = "0";
    if (showPercentage) defaultText += " - " + FormatNumber(100.0f, decimalPrecision) + "%";
    CreateBasicText(defaultText);
}

void QountersMinus::Qounters::NotesQounter::UpdateValue() {
    auto text = std::to_string(goodCuts) + "/" + std::to_string(allCuts);
    if (showPercentage) {
        text += " - " + FormatNumber((100.0f * goodCuts) / allCuts, decimalPrecision) + "%";
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
