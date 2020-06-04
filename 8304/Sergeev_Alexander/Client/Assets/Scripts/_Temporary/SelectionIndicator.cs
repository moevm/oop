using MonoBehaviours;
using Singletons;
using UnityEngine;


namespace _Temporary
{
    public class SelectionIndicator : MonoBehaviour
    {
        private static void RenderSelection(Renderer renderer, RectTransform rectTransform)
        {
            // Rect visualRect = RendererBoundsInScreenSpace(renderer);
            // rectTransform.position = new Vector2(visualRect.xMin, visualRect.yMin);
            // rectTransform.sizeDelta = new Vector2(visualRect.width, visualRect.height);
        }

        private static Rect RendererBoundsInScreenSpace(Renderer r)
        {
            // // This is the space occupied by the object's visuals in WORLD space.
            // Bounds bd = r.bounds;
            // Vector3[] screenSpaceCorners = new Vector3[8];
            //
            // // For each of the 8 corners of our renderer's world space bounding box,
            // // convert those corners into screen space.
            // screenSpaceCorners[0] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x + bd.extents.x,
            //     bd.center.y + bd.extents.y, bd.center.z + bd.extents.z));
            // screenSpaceCorners[1] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x + bd.extents.x,
            //     bd.center.y + bd.extents.y, bd.center.z - bd.extents.z));
            // screenSpaceCorners[2] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x + bd.extents.x,
            //     bd.center.y - bd.extents.y, bd.center.z + bd.extents.z));
            // screenSpaceCorners[3] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x + bd.extents.x,
            //     bd.center.y - bd.extents.y, bd.center.z - bd.extents.z));
            // screenSpaceCorners[4] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x - bd.extents.x,
            //     bd.center.y + bd.extents.y, bd.center.z + bd.extents.z));
            // screenSpaceCorners[5] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x - bd.extents.x,
            //     bd.center.y + bd.extents.y, bd.center.z - bd.extents.z));
            // screenSpaceCorners[6] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x - bd.extents.x,
            //     bd.center.y - bd.extents.y, bd.center.z + bd.extents.z));
            // screenSpaceCorners[7] = God.I.Cam.WorldToScreenPoint(new Vector3(bd.center.x - bd.extents.x,
            //     bd.center.y - bd.extents.y, bd.center.z - bd.extents.z));
            //
            // // Now find the min/max X & Y of these screen space corners.
            // float minX = screenSpaceCorners[0].x;
            // float minY = screenSpaceCorners[0].y;
            // float maxX = screenSpaceCorners[0].x;
            // float maxY = screenSpaceCorners[0].y;
            //
            // for (int i = 1; i < 8; i++)
            // {
            //     if (screenSpaceCorners[i].x < minX)
            //     {
            //         minX = screenSpaceCorners[i].x;
            //     }
            //     if (screenSpaceCorners[i].y < minY)
            //     {
            //         minY = screenSpaceCorners[i].y;
            //     }
            //     if (screenSpaceCorners[i].x > maxX)
            //     {
            //         maxX = screenSpaceCorners[i].x;
            //     }
            //     if (screenSpaceCorners[i].y > maxY)
            //     {
            //         maxY = screenSpaceCorners[i].y;
            //     }
            // }
            //
            // return Rect.MinMaxRect(minX, minY, maxX, maxY);
            return new Rect();
        }

        // Corner selection
        // GetComponentInChildren<Renderer>().enabled = true;
        //
        // Bounds bigBounds = mm.selectedObject.GetComponentInChildren<Renderer>().bounds;
        //
        // // This "diameter" only works correctly for relatively circular or square objects
        //
        // float padding = 1.0f;
        //
        //
        // this.transform.position = new Vector3(bigBounds.center.x, bigBounds.center.y, bigBounds.center.z);
        // this.transform.localScale = new Vector3( bigBounds.size.x*padding, bigBounds.size.y*padding, bigBounds.size.z*padding );
    }
}