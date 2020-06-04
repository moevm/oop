using System.Collections.Generic;
using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_ElementAnimationPreset gives a set of animations for a UI element.
    /// </summary>
    [CreateAssetMenu(fileName = "Element Animation Preset", menuName = "Quantum Tek/Quantum UI/Element Animation Preset")]
    public class QUI_ElementAnimationPreset : ScriptableObject
    {
        public new string name;
        public List<QUI_ElementAnimation> animations = new List<QUI_ElementAnimation>();
    }
}