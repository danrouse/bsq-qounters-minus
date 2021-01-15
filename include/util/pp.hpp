#pragma once

#include <map>
#include "util/logger.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/UnityWebRequestAsyncOperation.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include "UnityEngine/AsyncOperation.hpp"
#include "System/Action_1.hpp"

typedef struct _RawPPData {
    float _Easy_SoloStandard = 0.0f;
    float _Normal_SoloStandard = 0.0f;
    float _Hard_SoloStandard = 0.0f;
    float _Expert_SoloStandard = 0.0f;
    float _ExpertPlus_SoloStandard = 0.0f;
} RawPPData;

typedef System::Action_1<UnityEngine::AsyncOperation*>* DownloadCompleteDelegate;

namespace QountersMinus {
    namespace PP {
        static std::map<std::string, RawPPData> index;
        static UnityEngine::Networking::UnityWebRequest* request;

        void Initialize();
        void HandleWebRequestCompleted();

        bool SongAllowsPositiveModifiers(std::string songID);
        float CalculatePP(float maxPP, float accuracy);
        std::optional<float> BeatmapMaxPP(std::string songID, GlobalNamespace::BeatmapDifficulty difficulty);
    }
}
