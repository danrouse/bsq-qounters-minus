#pragma once

#include "logger.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus, Qounter, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, gameObject);

    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, Destroy);

    REGISTER_FUNCTION(Qounter,
        REGISTER_FIELD(gameObject);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(Destroy);
    )
)
