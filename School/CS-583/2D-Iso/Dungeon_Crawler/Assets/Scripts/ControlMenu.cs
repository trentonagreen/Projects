using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ControlMenu : MonoBehaviour
{
    public Text controlText;
    public Text moveText;
    public Text shootText;
    public Text backText;

    private void Awake()
    {
        controlText.text = "CONTROLS";
        moveText.text = "MOVEMENT";
        shootText.text = "SHOOT";
        backText.text = "BACK";
    }
}
