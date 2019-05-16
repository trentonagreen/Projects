using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Credits : MonoBehaviour
{
    public AudioClip CreditMusic;
    public AudioSource CreditMusicSource;

    void Start()
    {
        CreditMusicSource.clip = CreditMusic;
        CreditMusicSource.Play();
    }

    void Update()
    {
        if(Input.GetKey(KeyCode.Escape)) {
            SceneManager.LoadScene("MainMenu");
        }
    }
}
