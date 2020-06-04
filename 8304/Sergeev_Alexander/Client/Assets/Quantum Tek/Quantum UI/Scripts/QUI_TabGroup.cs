using System.Collections.Generic;
using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_TabAlign desides how the tabs are aligned on awake.
    /// </summary>
    [System.Serializable]
    public enum QUI_TabAlign
    {
        Left, Center, Right
    }

    /// <summary>
    /// QUI_TabGroup is a basic UI element responsible for holding QUI_TabWindows.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Tab Group")]
    [DisallowMultipleComponent]
    public class QUI_TabGroup : QUI_Element
    {
        [HideInInspector] public List<QUI_TabWindow> windows;
        [HideInInspector] public QUI_TabWindow currentWindow;

        [Header("Tab Group Variables")]
        [Tooltip("How the tabs should align.")]
        public QUI_TabAlign tabAlign;
        [Tooltip("How far the tabs should be from the side of the tab window when aligning to the left or right.")]
        public float sideOffset = 5;
        private bool aligned;

        public void Awake()
        {
            windows = new List<QUI_TabWindow>(GetComponentsInChildren<QUI_TabWindow>(true));

            foreach (var window in windows)
            {
                if (window.startActive)
                {
                    if (!currentWindow)
                        currentWindow = window;
                    else
                        window.startActive = false;
                }

                window.tab.startActive = window.startActive;
            }
        }

        public void Update()
        {
            if (!aligned)
            {
                AlignTabs(tabAlign);
                aligned = true;
            }

            if (active && currentWindow)
                currentWindow.SetActive(true);
        }

        /// <summary>
        /// Sets the active tab window of the group.
        /// </summary>
        /// <param name="window"></param>
        public void SetWindow(QUI_TabWindow window)
        {
            if (!windows.Contains(window))
                return;

            if (currentWindow)
                currentWindow.SetActive(false);
            currentWindow = window;
            if (currentWindow)
                currentWindow.SetActive(true);
        }

        /// <summary>
        /// Aligns the tabs to the given alignment.
        /// </summary>
        /// <param name="align"></param>
        public void AlignTabs(QUI_TabAlign align)
        {
            int tabCount = windows.Count;
            float tabsWidth = 0;
            tabAlign = align;

            for (int i = 0; i < tabCount; ++i)
            {
                RectTransform tabTransform;
                tabTransform = windows[i].tab.GetComponent<RectTransform>();
                if (!tabTransform) continue;
                tabsWidth += tabTransform.rect.width;
            }

            float currentTabWidth = 0;

            for (int i = 0; i < tabCount; ++i)
            {
                QUI_TabWindow window = windows[i];
                RectTransform tabTransform = window.tab.GetComponent<RectTransform>();
                float tabWidth = tabTransform.rect.width;

                if (align == QUI_TabAlign.Left)
                {
                    tabTransform.anchorMin = new Vector2(0, 1);
                    tabTransform.anchorMax = new Vector2(0, 1);
                    tabTransform.pivot = new Vector2(0, 0);
                    tabTransform.anchoredPosition = new Vector2(currentTabWidth + sideOffset, 0);
                    currentTabWidth += tabWidth;
                }
                else if (align == QUI_TabAlign.Center)
                {
                    tabTransform.anchorMin = new Vector2(0.5f, 1);
                    tabTransform.anchorMax = new Vector2(0.5f, 1);
                    tabTransform.pivot = new Vector2(0.5f, 0);
                    tabTransform.anchoredPosition = new Vector2(-tabsWidth / 2 + tabsWidth / 2 / tabCount + currentTabWidth, 0);
                    currentTabWidth += tabWidth;
                }
                else if (align == QUI_TabAlign.Right)
                {
                    currentTabWidth += tabWidth;
                    tabTransform.anchorMin = new Vector2(1, 1);
                    tabTransform.anchorMax = new Vector2(1, 1);
                    tabTransform.pivot = new Vector2(1, 0);
                    tabTransform.anchoredPosition = new Vector2(-tabsWidth + currentTabWidth - sideOffset, 0);
                }
            }
        }
    }
}