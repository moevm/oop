using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_TabWindow is a basic UI element responsible for holding other UI elements in a tab group.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Tab Window")]
    [DisallowMultipleComponent]
    public class QUI_TabWindow : QUI_Element
    {
        [Header("Tab Window Object References")]
        [Tooltip("The tab used to open the window.")]
        public QUI_Tab tab;

        public override void SetActive(bool value)
        {
            active = value;

            if (active)
                onActive.Invoke();
            else
                onInactive.Invoke();

            tab.SetActive(value);
        }
    }
}