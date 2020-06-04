using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_Tab is used for changing which tab window is shown in a tab group.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Tab")]
    [DisallowMultipleComponent]
    public class QUI_Tab : QUI_Element
    {
        public override void SetActive(bool value)
        {
            active = value;

            if (active)
                onActive.Invoke();
            else
                onInactive.Invoke();
        }
    }
}