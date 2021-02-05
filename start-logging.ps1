$timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
$bspid = adb shell pidof com.beatgames.beatsaber
# echo "PID"
# echo $bspid
while ([string]::IsNullOrEmpty($bspid)) {
    Start-Sleep -ms 100
    $bspid = adb shell pidof com.beatgames.beatsaber
}
adb logcat VrApi:S VrRuntimeClient:S OVRPlatform:S OVRPlugin:S OVRMrcLib:S AudioTrack:S `
    JniUtils:S Telemetry:S Metrics:S HeadsetReceiver:S UnityBatteryReceiver:S UnityVolumeReceiver:S libjingle:S `
    -T "$timestamp" --pid $bspid
# adb logcat -T "$timestamp" main-modloader:W QuestHook[qounters-minus`|v1.0.1]:* AndroidRuntime:E *:S
