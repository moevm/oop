using CaxapCommon.Enums;
using CaxapCommon.Ugui;
using CaxapCommon.Wrappers;
using JsonSchemas;
using Singletons;
using UnityEngine;
using UnityEngine.UI;


namespace GuiConcreteComponents.Session
{
    [ExecuteAlways]
    public class ButtonSetupGenerator : MonoBehaviour
    {
        public GeneratorType GeneratorType;

        private Button _button;
        
        public void Awake()
        {
            _button = GetComponent<Button>();
            _button.onClick.AddListener(() => God.NetworkManager.Send(new in_game_setup(GeneratorType)));
        }
    }
}