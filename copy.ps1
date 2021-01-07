& $PSScriptRoot/build.ps1
if ($?) {
    adb push libs/arm64-v8a/libqounters-minus.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libqounters-minus.so
    if ($?) {
        adb shell am force-stop com.beatgames.beatsaber
        adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
        if ($args[0] -eq "--log") {
            $timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
            adb logcat -T "$timestamp" main-modloader:W QuestHook[qounters-minus`|v0.1.0]:* AndroidRuntime:E *:S
        }
    }
}
