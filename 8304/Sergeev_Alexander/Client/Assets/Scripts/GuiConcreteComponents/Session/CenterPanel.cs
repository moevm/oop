using UnityEngine;


namespace GuiConcreteComponents.Session
{
    public class CenterPanel : MonoBehaviour
    {
        private static CenterPanel _instance;
        
        private void Awake()
        {
            _instance = this;
        }

        private void Start()
        {
        }

        public static void Foo()
        {
            
        }

        private void OnDestroy()
        {
            _instance = null;
        }
        
        // TODO draw selected units
    }
}