using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Flower : MonoBehaviour
{
    public DC_Character_Controller playerController;

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Fireball")
        {
            playerController.flowersDestroyed++;
            Destroy(gameObject);
        }
    }
}
