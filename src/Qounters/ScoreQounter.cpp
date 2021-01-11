#include "Qounters/ScoreQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::ScoreQounter);

void QountersMinus::Qounters::ScoreQounter::Configure(QountersMinus::ScoreQounterConfig config) {
    mode = (int)config.mode;
    customRankColors = config.customRankColors;
    decimalPrecision = config.decimalPrecision;
    ssColor = config.ssColor;
    sColor = config.sColor;
    aColor = config.aColor;
    bColor = config.bColor;
    cColor = config.cColor;
    dColor = config.dColor;
    eColor = config.eColor;

    CreateBasicTitle("Score");

    auto coreGameHUD = UnityEngine::Object::FindObjectOfType<GlobalNamespace::CoreGameHUDController*>();
    relativeScoreText = coreGameHUD->relativeScoreGO->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
    relativeScoreText->set_color(UnityEngine::Color::get_white());
    rankText = coreGameHUD->immediateRankGO->GetComponent<TMPro::TextMeshProUGUI*>();
    rankText->set_color(UnityEngine::Color::get_white());

    auto scoreUIController = coreGameHUD->GetComponentInChildren<GlobalNamespace::ScoreUIController*>();
    auto scoreUIText = scoreUIController->scoreText;
    scoreUIText->get_transform()->SetParent(gameObject->get_transform(), true);
    coreGameHUD->relativeScoreGO->get_transform()->SetParent(scoreUIText->get_transform(), true);
    coreGameHUD->immediateRankGO->get_transform()->SetParent(scoreUIText->get_transform(), true);

    // if (!mainConfig.ItalicText)
    // {
    //     old.fontStyle = relativeScoreText.fontStyle = rankText.fontStyle = FontStyles.Normal;
    //     Vector3 localPosition = relativeScoreText.rectTransform.localPosition;
    //     relativeScoreText.rectTransform.localPosition = new Vector3(0, localPosition.y, localPosition.z);
    //     localPosition = rankText.rectTransform.localPosition;
    //     rankText.rectTransform.localPosition = new Vector3(0, localPosition.y, localPosition.z);
    // }

    if (mode == (int)QountersMinus::ScoreQounterMode::RankOnly) UnityEngine::Object::Destroy(coreGameHUD->relativeScoreGO);
    if (mode == (int)QountersMinus::ScoreQounterMode::ScoreOnly) UnityEngine::Object::Destroy(coreGameHUD->immediateRankGO);

    // RectTransform pointsTextTransform = old.rectTransform;

    // HUDCanvas currentSettings = CanvasUtility.GetCanvasSettingsFromID(Settings.CanvasID);

    // Vector2 anchoredPos = CanvasUtility.GetAnchoredPositionFromConfig(Settings) + (offset * (3f / currentSettings.PositionScale));

    // pointsTextTransform.localPosition = anchoredPos * currentSettings.PositionScale;
    // pointsTextTransform.localPosition = new Vector3(pointsTextTransform.localPosition.x, pointsTextTransform.localPosition.y, 0);
    // pointsTextTransform.localEulerAngles = Vector3.zero;

    UnityEngine::Object::Destroy(coreGameHUD->GetComponentInChildren<GlobalNamespace::ImmediateRankUIPanel*>());

    relativeScoreAndImmediateRankCounter = UnityEngine::Object::FindObjectOfType<GlobalNamespace::RelativeScoreAndImmediateRankCounter*>();
    relativeScoreAndImmediateRankCounter->add_relativeScoreOrImmediateRankDidChangeEvent(il2cpp_utils::MakeDelegate<System::Action*>(
        classof(System::Action*), this, +[](QountersMinus::Qounters::ScoreQounter* self) {
            self->UpdateText();
        }
    ));
    UpdateText();
}

UnityEngine::Color QountersMinus::Qounters::ScoreQounter::GetRankColor(GlobalNamespace::RankModel::Rank rank) {
    switch (immediateRank) {
        case GlobalNamespace::RankModel::Rank::S: return sColor;
        case GlobalNamespace::RankModel::Rank::A: return aColor;
        case GlobalNamespace::RankModel::Rank::B: return bColor;
        case GlobalNamespace::RankModel::Rank::C: return cColor;
        case GlobalNamespace::RankModel::Rank::D: return dColor;
        case GlobalNamespace::RankModel::Rank::E: return eColor;
        default: return ssColor;
    }
}

void QountersMinus::Qounters::ScoreQounter::UpdateText() {
    auto immediateRank = relativeScoreAndImmediateRankCounter->immediateRank;
    if (immediateRank != prevImmediateRank) {
        rankText->set_text(GlobalNamespace::RankModel::GetRankName(immediateRank));
        prevImmediateRank = immediateRank;
        rankText->set_color(customRankColors ? GetRankColor(immediateRank) : UnityEngine::Color::get_white());
    }
    float relativeScore = relativeScoreAndImmediateRankCounter->relativeScore * 100.0f;
    relativeScoreText->set_text(il2cpp_utils::createcsstr(FormatNumber(relativeScore, decimalPrecision)));
}
