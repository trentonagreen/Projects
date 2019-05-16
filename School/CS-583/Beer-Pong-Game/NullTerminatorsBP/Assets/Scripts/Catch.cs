using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Catch : MonoBehaviour
{
    public GameObject player;
    public GameObject StartLocation;
    public GameObject CatchUI;

    private void OnTriggerEnter(Collider other)
    {
        if(other.CompareTag("Player"))
        {
            Debug.Log("Player fell of the platform");
            CatchUI.SetActive(true);
            Invoke("DeathRestart", 5);
        }
    }

    void DeathRestart()
    {
        SceneManager.LoadScene("Environment");
    }
}
