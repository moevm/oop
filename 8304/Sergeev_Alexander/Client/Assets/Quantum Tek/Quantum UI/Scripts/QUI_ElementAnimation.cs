using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_ElementAnimationType is responsible for how a UI element is animated.
    /// </summary>
    [System.Serializable]
    public enum QUI_ElementAnimationType
    {
        /// <summary> No animation will play. </summary>
        None,
        /// <summary> The AnimatorState with the QUI_ElementAnimation's name will play. </summary>
        Name,
        /// <summary> The AnimatorState with the QUI_ElementAnimation's trigger parameter will play. </summary>
        Trigger,
        /// <summary> The AnimatorState with the QUI_ElementAnimation's bool parameter will play. </summary>
        Bool,
        /// <summary> The AnimatorState with the QUI_ElementAnimation's int parameter will play. </summary>
        Int,
        /// <summary> The AnimatorState with the QUI_ElementAnimation's float parameter will play. </summary>
        Float
    }

    /// <summary>
    /// QUI_ElementAnimation is used for the animation of a UI element.
    /// </summary>
    [System.Serializable]
    public class QUI_ElementAnimation
    {
        [Tooltip("The name of the animation.")]
        public string name;
        [Tooltip("The type of the animation.")]
        public QUI_ElementAnimationType type;
        [Tooltip("The name of the animator parameter to use.")]
        public string parameterName;
        [Tooltip("The value to set the animator parameter to.")]
        public string parameterValue;

        /// <summary>
        /// Plays the animation starting at the given time.
        /// </summary>
        /// <param name="animator"></param>
        /// <param name="normalizedTime"></param>
        public void Play(Animator animator, float normalizedTime)
        {
            if (type == QUI_ElementAnimationType.None)
                return;
            if (type == QUI_ElementAnimationType.Name || !Mathf.Approximately(normalizedTime, 0))
                animator.Play(name, 0, normalizedTime);
            else if (type == QUI_ElementAnimationType.Trigger)
            {
                animator.ResetTrigger(parameterName);
                animator.SetTrigger(parameterName);
            }
            else if (type == QUI_ElementAnimationType.Bool)
                animator.SetBool(parameterName, bool.Parse(parameterValue));
            else if (type == QUI_ElementAnimationType.Int)
                animator.SetInteger(parameterName, int.Parse(parameterValue));
            else if (type == QUI_ElementAnimationType.Float)
                animator.SetFloat(parameterName, float.Parse(parameterValue));
        }

        /// <summary>
        /// Plays the animation from the start.
        /// </summary>
        /// <param name="animator"></param>
        public void Play(Animator animator)
        {
            Play(animator, 0);
        }
    }
}