$timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
$bspid = adb shell pidof com.beatgames.beatsaber
while ($bspid -eq "") {
    Start-Sleep -ms 100
    $bspid = adb shell pidof com.beatgames.beatsaber
}
adb logcat VrApi:S OVRPlatform:S -T "$timestamp" --pid $bspid
# adb logcat -T "$timestamp" main-modloader:W QuestHook[qounters-minus`|v1.0.1]:* AndroidRuntime:E *:S
