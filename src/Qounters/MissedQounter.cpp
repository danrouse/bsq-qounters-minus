#include "Qounters/MissedQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::MissedQounter);

void QountersMinus::Qounters::MissedQounter::Configure(QountersMinus::MissedQounterConfig config) {
    countBadCuts = config.countBadCuts;

    CreateBasicTitle("Misses");
    CreateBasicText("0");
}

void QountersMinus::Qounters::MissedQounter::UpdateValue() {
    basicText->set_text(il2cpp_utils::createcsstr(std::to_string(misses)));
}

void QountersMinus::Qounters::MissedQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (countBadCuts && !info->get_allIsOK() && data->colorType != GlobalNamespace::ColorType::None) {
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
