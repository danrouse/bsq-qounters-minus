#include "Qounters/ScoreQounter.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::Qounters::ScoreQounter);

QountersMinus::Qounter* QountersMinus::Qounters::ScoreQounter::Initialize() {
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::ScoreQounter*>(
        config.ScoreQounterConfig.position, config.ScoreQounterConfig.distance
    );
}

void QountersMinus::Qounters::ScoreQounter::Start() {
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

    if (config.ScoreQounterConfig.mode == QountersMinus::ScoreQounterMode::RankOnly)
        UnityEngine::Object::Destroy(coreGameHUD->relativeScoreGO);
    if (config.ScoreQounterConfig.mode == QountersMinus::ScoreQounterMode::ScoreOnly)
        UnityEngine::Object::Destroy(coreGameHUD->immediateRankGO);

    // instead of calculating original text position based on canvas like counters+,
    // just slap that bad boy right on our unpopulated gameobject
    auto basePosition = gameObject->get_transform()->get_position();
    scoreUIText->get_transform()->set_position(basePosition);

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
        case GlobalNamespace::RankModel::Rank::S: return config.ScoreQounterConfig.sColor;
        case GlobalNamespace::RankModel::Rank::A: return config.ScoreQounterConfig.aColor;
        case GlobalNamespace::RankModel::Rank::B: return config.ScoreQounterConfig.bColor;
        case GlobalNamespace::RankModel::Rank::C: return config.ScoreQounterConfig.cColor;
        case GlobalNamespace::RankModel::Rank::D: return config.ScoreQounterConfig.dColor;
        case GlobalNamespace::RankModel::Rank::E: return config.ScoreQounterConfig.eColor;
        default: return config.ScoreQounterConfig.ssColor;
    }
}

void QountersMinus::Qounters::ScoreQounter::UpdateText() {
    auto immediateRank = relativeScoreAndImmediateRankCounter->immediateRank;
    if (immediateRank != prevImmediateRank) {
        rankText->set_text(GlobalNamespace::RankModel::GetRankName(immediateRank));
        prevImmediateRank = immediateRank;
        rankText->set_color(config.ScoreQounterConfig.customRankColors ? GetRankColor(immediateRank) : UnityEngine::Color::get_white());
    }
    float relativeScore = relativeScoreAndImmediateRankCounter->relativeScore * 100.0f;
    relativeScoreText->set_text(il2cpp_utils::createcsstr(FormatNumber(relativeScore, config.ScoreQounterConfig.decimalPrecision) + "%"));
}
