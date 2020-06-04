using System.Collections.Generic;
using MonoBehaviours.Elements;
using UnityEngine;


namespace MonoBehaviours.Session
{
    public class SelectionBehaviour : MonoBehaviour
    {
        private static SelectionBehaviour _instance;

        private List<UnitBehaviour> _selection; //TODO

        private void Awake()
        {
            _instance = this;
        }

        private void OnDestroy()
        {
            _instance = null;
        }

        public static List<int> GetSelection()
        {
            return new List<int>() {1111, 2222, 3333};
        }
    }
}