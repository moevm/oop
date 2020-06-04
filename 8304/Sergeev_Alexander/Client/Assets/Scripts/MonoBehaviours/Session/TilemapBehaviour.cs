using System.Collections.Generic;
using JsonSchemas.Tilemap;
using JsonSchemas.Tiles;
using MonoBehaviours.Elements;
using UnityEngine;


namespace MonoBehaviours.Session
{
    public class TilemapBehaviour : MonoBehaviour
    {
        public TileBehaviour TilePrefab;
        public Transform ParentTransform;

        private static TilemapBehaviour _instance;
        private TileBehaviour[,] _tilemap; //TODO

        private void Awake()
        {
            _instance = this;
        }

        private void OnDestroy()
        {
            _instance = null;
        }

        public static void DrawTilemap(abstract_tilemap tilemap)
        {
            if (!_instance) return;
            if (_instance._tilemap != null)
            {
                foreach (TileBehaviour tile in _instance._tilemap)
                {
                    Destroy(tile.gameObject); // TODO
                }
            }
            _instance._tilemap = new TileBehaviour[tilemap.scale.x, tilemap.scale.y];
            for (int y = 0; y < tilemap.scale.y; y++)
            {
                for (int x = 0; x < tilemap.scale.x; x++)
                {
                    base_tile tile = tilemap.data[y * tilemap.scale.x + x];
                    Vector3 position = tilemap.GetPosition(x, y, tile); // TODO
                    TileBehaviour tileBehaviour = Instantiate(_instance.TilePrefab, position, Quaternion.identity, _instance.ParentTransform);
                    tileBehaviour.DrawTile(tile);
                    _instance._tilemap[x, y] = tileBehaviour;
                }
            }
        }
    }
}