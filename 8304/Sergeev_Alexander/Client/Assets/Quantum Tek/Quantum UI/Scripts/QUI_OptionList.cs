using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using TMPro;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_OptionList offers multiple strings to choose from using buttons.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Option List")]
    [DisallowMultipleComponent]
    public class QUI_OptionList : MonoBehaviour
    {
        [Header("Option List Object References")]
        [Tooltip("The text to show the current option.")]
        public TextMeshProUGUI optionText;

        [Header("Option List Variables")]
        [Tooltip("The list of option choices.")]
        public List<string> options;
        [Tooltip("The event invoked on changing the current option.")]
        public UnityEvent onChangeOption;
        [HideInInspector] public int optionIndex;
        [HideInInspector] public string option;

        public void Awake()
        {
            SetOption(optionIndex);
        }

        /// <summary>
        /// Sets the chosen option to the one given.
        /// </summary>
        /// <param name="index"></param>
        public void SetOption(int index)
        {
            optionIndex = index;
            option = options[optionIndex];
            optionText.text = option;
        }

        /// <summary>
        /// Increments/decrements the current option by the given amount.
        /// </summary>
        /// <param name="direction"></param>
        public void ChangeOption(int direction)
        {
            optionIndex += direction;

            if (optionIndex < 0)
                optionIndex = options.Count - 1;
            else if (optionIndex >= options.Count)
                optionIndex = 0;

            SetOption(optionIndex);
            onChangeOption.Invoke();
        }
    }
}