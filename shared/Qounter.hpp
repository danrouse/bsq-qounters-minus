#pragma once

#include <map>
#include "util/logger.hpp"
#include "InjectedComponents.hpp"
#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

// define version for external consumers
#define QOUNTERS_MINUS_VERSION "1.0.2"

namespace QountersMinus {
    enum class QounterPosition {
        BelowCombo,
        AboveCombo,
        BelowMultiplier,
        AboveMultiplier,
        BelowEnergy,
        AboveHighway
    };
    static int QounterPositionCount = 6;
    static std::unordered_map<int, std::string> QounterPositionNames = {
        {static_cast<int>(QounterPosition::BelowCombo), "Below Combo"},
        {static_cast<int>(QounterPosition::AboveCombo), "Above Combo"},
        {static_cast<int>(QounterPosition::BelowMultiplier), "Below Multiplier"},
        {static_cast<int>(QounterPosition::AboveMultiplier), "Above Multiplier"},
        {static_cast<int>(QounterPosition::BelowEnergy), "Below Energy"},
        {static_cast<int>(QounterPosition::AboveHighway), "Over Highway"}
    };
    static std::unordered_map<std::string, int> QounterPositionLookup = {
        {"BelowCombo", static_cast<int>(QounterPosition::BelowCombo)},
        {"AboveCombo", static_cast<int>(QounterPosition::AboveCombo)},
        {"BelowMultiplier", static_cast<int>(QounterPosition::BelowMultiplier)},
        {"AboveMultiplier", static_cast<int>(QounterPosition::AboveMultiplier)},
        {"BelowEnergy", static_cast<int>(QounterPosition::BelowEnergy)},
        {"AboveHighway", static_cast<int>(QounterPosition::AboveHighway)}
    };
}

UnityEngine::GameObject* GetParent(QountersMinus::QounterPosition position);
void SetPosition(UnityEngine::Transform* transform, QountersMinus::QounterPosition position, float distance);

DECLARE_CLASS_CODEGEN(QountersMinus, Qounter, UnityEngine::MonoBehaviour,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(bool, HideCombo);
    DECLARE_STATIC_FIELD(bool, HideMultiplier);
    DECLARE_STATIC_FIELD(float, ComboOffset);
    DECLARE_STATIC_FIELD(float, MultiplierOffset);
    DECLARE_STATIC_FIELD(bool, ItalicText);
    DECLARE_STATIC_FIELD(bool, UprightInMultiplayer);
    DECLARE_STATIC_FIELD(bool, DisableIn90Degree);
    DECLARE_STATIC_FIELD(float, DistanceStep);

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, gameObject);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, basicText);
    DECLARE_INSTANCE_FIELD(QountersMinus::InjectedComponents*, refs);

    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, OnDestroy);

    REGISTER_FUNCTION(Qounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(HideCombo);
        REGISTER_FIELD(HideMultiplier);
        REGISTER_FIELD(ComboOffset);
        REGISTER_FIELD(MultiplierOffset);
        REGISTER_FIELD(ItalicText);
        REGISTER_FIELD(UprightInMultiplayer);
        REGISTER_FIELD(DisableIn90Degree);
        REGISTER_FIELD(DistanceStep);

        REGISTER_FIELD(gameObject);
        REGISTER_FIELD(basicText);
        REGISTER_FIELD(refs);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(OnDestroy);
    )

    public:
        TMPro::TextMeshProUGUI* CreateBasicTitle(std::string text);
        void CreateBasicText(std::string text);
        static Qounter* Initialize(System::Type* type, QountersMinus::QounterPosition position, float distance);
)
