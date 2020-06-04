using System.Collections.Generic;
using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_ElementAudioPreset gives a set of audio clips for a UI element.
    /// </summary>
    [CreateAssetMenu(fileName = "Element Audio Preset", menuName = "Quantum Tek/Quantum UI/Element Audio Preset")]
    public class QUI_ElementAudioPreset : ScriptableObject
    {
        public new string name;
        public List<QUI_ElementAudioClip> clips = new List<QUI_ElementAudioClip>();
    }
}