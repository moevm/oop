using JsonSchemas.Structs;
using Singletons;
using TMPro;
using UnityEngine;


namespace GuiConcreteComponents.Session
{
    public class PlayersScrollListItem : MonoBehaviour
    {
        public TMP_Text PlayerText;

        public void VisualizeData(int uid)
        {
            // TODO
            PlayerText.text = $"{God.NetworkManager.GetUsernameById(uid)}";
            // TODO
        }
        
        public void VisualizeData(int uid, player player)
        {
            // TODO
            PlayerText.text = $"{God.NetworkManager.GetUsernameById(uid)} - {player.team} team";
            // TODO
        }
    }
}