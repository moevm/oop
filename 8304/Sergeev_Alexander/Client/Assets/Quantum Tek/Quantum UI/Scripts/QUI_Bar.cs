using UnityEngine;
using UnityEngine.UI;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_BarFillType determines how a bar is filled.
    /// </summary>
    [System.Serializable]
    public enum QUI_BarFillType
    {
        Width, Height, FillAmount
    }

    /// <summary>
    /// QUI_Bar represents any type of UI bar, such as a health or progress bar.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Bar")]
    [DisallowMultipleComponent]
    public class QUI_Bar : MonoBehaviour
    {
        [Header("Bar Object References")]
        [Tooltip("The bar used as a background and mask.")]
        public RectTransform barTransform;
        [Tooltip("The fill image transform.")]
        public RectTransform fillTransform;
        [Tooltip("The fill image.")]
        public Image fill;
        
        [Header("Bar Variables")]
        [Tooltip("How the bar fills up.")]
        public QUI_BarFillType fillType;
        [Tooltip("Used as the fill amount of the bar, including at the start.")]
        public float fillAmount;

        private void Start()
        {
            SetFill(fillAmount);
        }

        /// <summary>
        /// Sets the fill amount of the bar.
        /// </summary>
        /// <param name="amount"></param>
        public void SetFill(float amount)
        {
            fillAmount = amount;

            if (fillType == QUI_BarFillType.FillAmount)
                fill.fillAmount = amount;
            else if (fillType == QUI_BarFillType.Width)
                fillTransform.SetSizeWithCurrentAnchors(RectTransform.Axis.Horizontal, amount * barTransform.rect.width);
            else if (fillType == QUI_BarFillType.Height)
                fillTransform.SetSizeWithCurrentAnchors(RectTransform.Axis.Vertical, amount * barTransform.rect.height);
        }
    }
}