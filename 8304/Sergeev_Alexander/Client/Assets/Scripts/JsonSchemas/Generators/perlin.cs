using System.Collections.Generic;
using JsonSchemas.Structs;
// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Generators
{
    public class perlin : abstract_generator
    {
        public int seed;
        public int octaves;
        public float persistance;
        public List<int> players_uid;
        public vector2<int> tilemap_scale;

        public perlin(int seed, int octaves, float persistance, List<int> playersUid, int tilemapScaleX, int tilemapScaleY)
        {
            this.seed = seed;
            this.octaves = octaves;
            this.persistance = persistance;
            this.players_uid = playersUid;
            this.tilemap_scale = new vector2<int>(tilemapScaleX, tilemapScaleY);
        }

        public override bool IsValid()
        {
            return players_uid != null && seed > 0 && octaves > 0 && persistance > 0 && persistance < 1 && players_uid.Count != 0 && tilemap_scale.x > 8 && tilemap_scale.y > 8;
        }
    }
}