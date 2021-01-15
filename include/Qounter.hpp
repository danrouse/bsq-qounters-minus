#pragma once

#include "config.hpp"
#include "config/QounterConfig.hpp"
#include "util/logger.hpp"
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

UnityEngine::GameObject* GetParent(QountersMinus::QounterPosition position);
void SetPosition(UnityEngine::Transform* transform, QountersMinus::QounterPosition position, int distance);

DECLARE_CLASS_CODEGEN(QountersMinus, Qounter, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, gameObject);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, basicText);

    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, OnDestroy);

    REGISTER_FUNCTION(Qounter,
        REGISTER_FIELD(gameObject);
        REGISTER_FIELD(basicText);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(OnDestroy);
    )

    public:
        TMPro::TextMeshProUGUI* CreateBasicTitle(std::string text);
        void CreateBasicText(std::string text);

        template<typename T>
        static T Initialize(QountersMinus::QounterPosition position, float distance) {
            auto parent = GetParent(position);
            auto instance = parent->AddComponent<T>();
            SetPosition(instance->gameObject->get_transform(), position, distance);
            return instance;
        }
)
