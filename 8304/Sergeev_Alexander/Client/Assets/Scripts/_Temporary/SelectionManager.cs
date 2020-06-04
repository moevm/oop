using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;


namespace MonoBehaviours
{
    public class SelectionManager : MonoBehaviour
    {
        [SerializeField]
        private LayerMask GroundMask;

        [SerializeField]
        private LayerMask UnitMask;

        [SerializeField]
        private RectTransform SelectionBoxTransform;

        private CanvasScaler _canvasScaler;

        private Vector3 _startPos;

        private bool _isSelectionStarted;

        private void Start()
        {
            // SelectionBoxTransform.gameObject.SetActive(false);
            // _canvasScaler = SelectionBoxTransform.GetComponentInParent<CanvasScaler>();
            // _isSelectionStarted = false;
        }

        private void Update()
        {
            // if (Input.GetMouseButtonDown(0) && !EventSystem.current.IsPointerOverGameObject())
            // {
            //     if (Physics.Raycast(God.I.Cam.ScreenPointToRay(Input.mousePosition), out RaycastHit hit,
            //         Mathf.Infinity, GroundMask))
            //     {
            //         _startPos = hit.point;
            //         _isSelectionStarted = true;
            //     }
            // }
            //
            // if (Input.GetMouseButtonUp(0) && _isSelectionStarted)
            // {
            //     if (!Input.GetKey(KeyCode.LeftControl) && !Input.GetKey(KeyCode.RightControl))
            //     {
            //         ClearSelection();
            //     }
            //     
            //     if (Physics.Raycast(God.I.Cam.ScreenPointToRay(Input.mousePosition), out RaycastHit groundHit,
            //         Mathf.Infinity, GroundMask))
            //     {
            //         Vector2 startPoint = God.I.Cam.WorldToScreenPoint(_startPos);
            //         Vector2 stopPoint = God.I.Cam.WorldToScreenPoint(groundHit.point);
            //         SelectUnits(new Rect(startPoint, stopPoint - startPoint));
            //     }
            //     _isSelectionStarted = false;
            // }
            //
            // if (Input.GetMouseButton(0) && _isSelectionStarted)
            // {
            //     DrawSelection();
            // }
        }

        private void ClearSelection()
        {
            // foreach (Unit unit in God.I.SelectedUnits)
            // {
            //     unit.Deselect();
            // }
            // God.I.SelectedUnits.Clear();
        }

        private void SelectUnits(Rect selectionRect)
        {
            // if (selectionRect.size.sqrMagnitude < 0.1f)
            // {
            //     if (Physics.Raycast(God.I.Cam.ScreenPointToRay(Input.mousePosition), out RaycastHit unitHit,
            //         Mathf.Infinity, UnitMask))
            //     {
            //         Unit unit = unitHit.transform.GetComponent<Unit>();
            //         if (unit && !God.I.SelectedUnits.Contains(unit))
            //         {
            //             unit.Select();
            //             God.I.SelectedUnits.Add(unit);
            //         }
            //     }
            // }
            // else
            // {
            //     foreach (Unit unit in God.I.Units)
            //     {
            //         Vector2 point = God.I.Cam.WorldToScreenPoint(unit.transform.position);
            //         if (selectionRect.Contains(point, true))
            //         {
            //             unit.Select();
            //             God.I.SelectedUnits.Add(unit);
            //         }
            //     }
            // }
            //
            // SelectionBoxTransform.gameObject.SetActive(false);
        }

        private void DrawSelection()
        {
            // if (!SelectionBoxTransform.gameObject.activeSelf)
            // {
            //     SelectionBoxTransform.gameObject.SetActive(true);
            // }
            // Vector2 refResolution = _canvasScaler.referenceResolution;
            // Vector2 scaleReference = new Vector2(refResolution.x / Screen.width, refResolution.y / Screen.height);
            //
            // Vector3 startPoint = God.I.Cam.WorldToScreenPoint(_startPos);
            // startPoint.z = 0;
            //
            // Vector3 endPoint = Input.mousePosition;
            // Vector3 center = (startPoint + endPoint) / 2;
            //
            // float width = Mathf.Abs(startPoint.x - endPoint.x);
            // float height = Mathf.Abs(startPoint.y - endPoint.y);
            //
            // SelectionBoxTransform.position = center;
            // Vector2 scaledSize = new Vector2(width, height);
            // scaledSize.Scale(scaleReference);
            // SelectionBoxTransform.sizeDelta = scaledSize;
        }
    }
}