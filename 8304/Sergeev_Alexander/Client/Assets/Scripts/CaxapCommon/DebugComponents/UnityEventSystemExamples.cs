using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;


namespace UnityEventSystemExamples
{
    public class ClickDetector : MonoBehaviour, IPointerDownHandler, IPointerClickHandler,
        IPointerUpHandler, IPointerExitHandler, IPointerEnterHandler,
        IBeginDragHandler, IDragHandler, IEndDragHandler
    {
        public void OnBeginDrag(PointerEventData eventData)
        {
            Debug.Log("Drag Begin");
        }

        public void OnDrag(PointerEventData eventData)
        {
            Debug.Log("Dragging");
        }

        public void OnEndDrag(PointerEventData eventData)
        {
            Debug.Log("Drag Ended");
        }

        public void OnPointerClick(PointerEventData eventData)
        {
            Debug.Log("Clicked: " + eventData.pointerCurrentRaycast.gameObject.name);
        }

        public void OnPointerDown(PointerEventData eventData)
        {
            Debug.Log("Mouse Down: " + eventData.pointerCurrentRaycast.gameObject.name);
        }

        public void OnPointerEnter(PointerEventData eventData)
        {
            Debug.Log("Mouse Enter");
        }

        public void OnPointerExit(PointerEventData eventData)
        {
            Debug.Log("Mouse Exit");
        }

        public void OnPointerUp(PointerEventData eventData)
        {
            Debug.Log("Mouse Up");
        }
    }


    public class ButtonClickDetector : MonoBehaviour
    {
        public Button button1;
        public Button button2;
        public Button button3;

        void OnEnable()
        {
            //Register Button Events
            button1.onClick.AddListener(() => buttonCallBack(button1));
            button2.onClick.AddListener(() => buttonCallBack(button2));
            button3.onClick.AddListener(() => buttonCallBack(button3));
        }

        private void buttonCallBack(Button buttonPressed)
        {
            if (buttonPressed == button1)
            {
                //Your code for button 1
                Debug.Log("Clicked: " + button1.name);
            }

            if (buttonPressed == button2)
            {
                //Your code for button 2
                Debug.Log("Clicked: " + button2.name);
            }

            if (buttonPressed == button3)
            {
                //Your code for button 3
                Debug.Log("Clicked: " + button3.name);
            }
        }

        void OnDisable()
        {
            //Un-Register Button Events
            button1.onClick.RemoveAllListeners();
            button2.onClick.RemoveAllListeners();
            button3.onClick.RemoveAllListeners();
        }
    }


    public class InputFieldEvents : MonoBehaviour
    {
        public InputField inputField;

        void OnEnable()
        {
            //Register InputField Events
            inputField.onEndEdit.AddListener(delegate { inputEndEdit(); });
            inputField.onValueChanged.AddListener(delegate { inputValueChanged(); });
        }

        //Called when Input is submitted
        private void inputEndEdit()
        {
            Debug.Log("Input Submitted");
        }

        //Called when Input changes
        private void inputValueChanged()
        {
            Debug.Log("Input Changed");
        }

        void OnDisable()
        {
            //Un-Register InputField Events
            inputField.onEndEdit.RemoveAllListeners();
            inputField.onValueChanged.RemoveAllListeners();
        }
    }


    public class SliderEvents : MonoBehaviour
    {
        public Slider slider;

        void OnEnable()
        {
            //Subscribe to the Slider Click event
            slider.onValueChanged.AddListener(delegate { sliderCallBack(slider.value); });
        }

        //Will be called when Slider changes
        void sliderCallBack(float value)
        {
            Debug.Log("Slider Changed: " + value);
        }

        void OnDisable()
        {
            //Un-Subscribe To Slider Event
            slider.onValueChanged.RemoveListener(delegate { sliderCallBack(slider.value); });
        }
    }


    public class DropdownEvents : MonoBehaviour
    {
        public Dropdown dropdown;
        void OnEnable()
        {
            //Register to onValueChanged Events

            //Callback with parameter
            dropdown.onValueChanged.AddListener(delegate { callBack(); });

            //Callback without parameter
            dropdown.onValueChanged.AddListener(callBackWithParameter);
        }

        void OnDisable()
        {
            //Un-Register from onValueChanged Events
            dropdown.onValueChanged.RemoveAllListeners();
        }

        void callBack()
        {

        }

        void callBackWithParameter(int value)
        {

        }
    }
    
    public class MeshDetector : MonoBehaviour, IPointerDownHandler
    {
        void Start()
        {
            addPhysicsRaycaster();
        }

        void addPhysicsRaycaster()
        {
            PhysicsRaycaster physicsRaycaster = GameObject.FindObjectOfType<PhysicsRaycaster>();
            if (physicsRaycaster == null)
            {
                Camera.main.gameObject.AddComponent<PhysicsRaycaster>();
            }
        }

        public void OnPointerDown(PointerEventData eventData)
        {
            Debug.Log("Clicked: " + eventData.pointerCurrentRaycast.gameObject.name);
        }

        //Implement Other Events from Method 1
    }
    
    public class SpriteDetector : MonoBehaviour, IPointerDownHandler
    {
        void Start()
        {
            addPhysics2DRaycaster();
        }

        void addPhysics2DRaycaster()
        {
            Physics2DRaycaster physicsRaycaster = GameObject.FindObjectOfType<Physics2DRaycaster>();
            if (physicsRaycaster == null)
            {
                Camera.main.gameObject.AddComponent<Physics2DRaycaster>();
            }
        }

        public void OnPointerDown(PointerEventData eventData)
        {
            Debug.Log("Clicked: " + eventData.pointerCurrentRaycast.gameObject.name);
        }

        //Implement Other Events from Method 1
    }
}