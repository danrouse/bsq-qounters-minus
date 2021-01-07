#pragma once

#include <map>
#include "logger.hpp"
#include "Qounter.hpp"
#include "Qounters/CutQounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/Transform.hpp"

namespace QountersMinus {
    typedef enum _QounterType {
        CutQounter,
        FailQounter,
        MissedQounter,
        NotesQounter,
        NotesLeftQounter,
        PBQounter,
        ProgressBaseGameQounter,
        ProgressQounter,
        ScoreQounter,
        SpeedQounter
    } QounterType;
    
    typedef enum _QounterPosition {
        BelowCombo,
        AboveCombo,
        BelowMultiplier,
        AboveMultiplier,
        BelowEnergy,
        OverHighway
    } QounterPosition;

    typedef struct _QounterConfig {
        QounterType type;
        QounterPosition position;
    } QounterConfig;

    class QounterRegistry {
        private:
            inline static std::vector<QountersMinus::Qounter*> registry;
        public:
            static void RegisterTypes();
            static void Initialize(QounterConfig config);
            static void DestroyAll();
            static void OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
            static void OnNoteMiss(GlobalNamespace::NoteData* data);
            static void ScoreUpdated(int modifiedScore);
            static void MaxScoreUpdated(int maxModifiedScore);
    };
};

// DECLARE_CLASS_CODEGEN(QountersMinus, QounterRegistry, Il2CppObject,
//     DECLARE_STATIC_FIELD(::Array<QountersMinus::Qounter*>*, registry);
//     DECLARE_METHOD(static void, DestroyAll);

//     DECLARE_METHOD(static void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
//     DECLARE_METHOD(static void, OnNoteMiss, GlobalNamespace::NoteData* data);
//     DECLARE_METHOD(static void, ScoreUpdated, int modifiedScore);
//     DECLARE_METHOD(static void, MaxScoreUpdated, int maxModifiedScore);

//     REGISTER_FUNCTION(QounterRegistry,
//         REGISTER_FIELD(registry);
//         REGISTER_METHOD(DestroyAll);

//         REGISTER_METHOD(OnNoteCut);
//         REGISTER_METHOD(OnNoteMiss);
//         REGISTER_METHOD(ScoreUpdated);
//         REGISTER_METHOD(MaxScoreUpdated);
//     )

//     public:
//     static void Initialize(QountersMinus::Config config);
// )
