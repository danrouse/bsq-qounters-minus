#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"

#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus, Qounter, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, gameObject);

    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, Destroy);

    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, ScoreUpdated, int modifiedScore);
    DECLARE_METHOD(void, MaxScoreUpdated, int maxModifiedScore);

    REGISTER_FUNCTION(Qounter,
        REGISTER_FIELD(gameObject);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(Destroy);
        
        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(ScoreUpdated);
        REGISTER_METHOD(MaxScoreUpdated);
    )
)
