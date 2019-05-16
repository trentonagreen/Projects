using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Portal : MonoBehaviour
{
    public Animator animator;
    public DC_Character_Controller playerController;

    public bool bossPortal = false;

    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            Debug.Log("Player Entered Trigger");
            if(playerController.hasGem == true)
            {
                animator.SetBool("Activate_Portal", true);
            }
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            Debug.Log("Player Exited Trigger");
            animator.SetBool("Activate_Portal", false);
        }
    }

    void OnTriggerStay(Collider other)
    {
        if (other.tag == "Player")
        {
            Debug.Log("Player is still on Trigger");
            if (playerController.hasGem == true)
            {
                animator.SetBool("Activate_Portal", true);

                if (bossPortal == false)
                {
                    Invoke("LoadBossScene", 3f);
                }
                if(bossPortal == true)
                {
                    Invoke("LoadCredits", 3f);
                }
            }
        }
    }

    void LoadBossScene()
    {
        SceneManager.LoadScene("Boss");
    }

    void LoadCredits()
    {
        SceneManager.LoadScene("Credits");
    }
}
