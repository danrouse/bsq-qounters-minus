#include "Qounters/ScoreQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::ScoreQounter);

// TODO: don't do this
#include "config.hpp"
extern QountersMinus::ModConfig config;

void QountersMinus::Qounters::ScoreQounter::Configure(QountersMinus::ScoreQounterConfig _config) {
    mode = (int)_config.mode;
    customRankColors = _config.customRankColors;
    decimalPrecision = _config.decimalPrecision;
    ssColor = _config.ssColor;
    sColor = _config.sColor;
    aColor = _config.aColor;
    bColor = _config.bColor;
    cColor = _config.cColor;
    dColor = _config.dColor;
    eColor = _config.eColor;

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

    if (!config.italicText) {
        scoreUIText->set_fontStyle(TMPro::FontStyles::Normal);
        relativeScoreText->set_fontStyle(TMPro::FontStyles::Normal);
        rankText->set_fontStyle(TMPro::FontStyles::Normal);
        auto localPosition1 = relativeScoreText->get_rectTransform()->get_localPosition();
        relativeScoreText->get_rectTransform()->set_localPosition(UnityEngine::Vector3(0.0f, localPosition1.y, localPosition1.z));
        auto localPosition2 = rankText->get_rectTransform()->get_localPosition();
        rankText->get_rectTransform()->set_localPosition(UnityEngine::Vector3(0.0f, localPosition2.y, localPosition2.z));
    }

    if (mode == (int)QountersMinus::ScoreQounterMode::RankOnly) UnityEngine::Object::Destroy(coreGameHUD->relativeScoreGO);
    if (mode == (int)QountersMinus::ScoreQounterMode::ScoreOnly) UnityEngine::Object::Destroy(coreGameHUD->immediateRankGO);

    // HUDCanvas currentSettings = CanvasUtility.GetCanvasSettingsFromID(Settings.CanvasID);
    // Vector2 anchoredPos = CanvasUtility.GetAnchoredPositionFromConfig(Settings) + (offset * (3f / currentSettings.PositionScale));
    // scoreUIText.rectTransform.localPosition = anchoredPos * currentSettings.PositionScale;
    // scoreUIText.rectTransform.localPosition = new Vector3(scoreUIText.rectTransform.localPosition.x, scoreUIText.rectTransform.localPosition.y, 0);
    // scoreUIText.rectTransform.localEulerAngles = Vector3.zero;

    // WIP porting that from above
    // auto scoreUITextRect = scoreUIText->get_rectTransform();
    // scoreUITextRect->set_localPosition(UnityEngine::Vector3(
    //     scoreUITextRect->get_localPosition().x * anchoredPos * currentSettings.positionScale,
    //     scoreUITextRect->get_localPosition().y * anchoredPos * currentSettings.positionScale,
    //     0.0f
    // ));
    // scoreUITextRect->set_localEulerAngles(UnityEngine::Vector3::get_zero());

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
    switch (rank) {
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
