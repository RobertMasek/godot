using Godot;
using GodotTools.Internals;
using JetBrains.Annotations;
using static GodotTools.Internals.Globals;

namespace GodotTools
{
    public partial class HotReloadAssemblyWatcher : Node
    {
        private Timer _watchTimer;

        public override void _Notification(int what)
        {
            if (what == Node.NotificationWmWindowFocusIn)
            {
                RestartTimer();

                if (Internal.IsAssembliesReloadingNeeded())
                    Internal.ReloadAssemblies(softReload: false);
            }
        }

        private void TimerTimeout()
        {
            if (Internal.IsAssembliesReloadingNeeded())
                Internal.ReloadAssemblies(softReload: false);
        }

        [UsedImplicitly]
        public void RestartTimer()
        {
            _watchTimer.Stop();
            _watchTimer.Start();
        }

        public override void _Ready()
        {
            base._Ready();

            _watchTimer = new Timer
            {
                OneShot = false,
                WaitTime = (float)EditorDef("mono/assembly_watch_interval_sec", 0.5)
            };
            _watchTimer.Timeout += TimerTimeout;
            AddChild(_watchTimer);
            _watchTimer.Start();
        }
    }
}
