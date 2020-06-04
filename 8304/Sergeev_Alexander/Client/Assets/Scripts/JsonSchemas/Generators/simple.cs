using System.Collections.Generic;
using JsonSchemas.Structs;
// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Generators
{
    public class simple : abstract_generator
    {
        public int seed;
        public List<int> players_uid;
        public vector2<int> tilemap_scale;

        public simple(int seed, List<int> playersUid, int tilemapScaleX, int tilemapScaleY)
        {
            this.seed = seed;
            this.players_uid = playersUid;
            this.tilemap_scale = new vector2<int>(tilemapScaleX, tilemapScaleY);
        }

        public override bool IsValid()
        {
            return players_uid != null && players_uid.Count != 0 && tilemap_scale.x != 0 && tilemap_scale.y != 0;
        }
    }
}