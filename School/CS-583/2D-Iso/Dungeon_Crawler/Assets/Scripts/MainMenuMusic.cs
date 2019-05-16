using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainMenuMusic : MonoBehaviour
{
    public AudioClip MenuClip;
    public AudioSource MenuSource;

    // Start is called before the first frame update
    void Start()
    {
        MenuSource.clip = MenuClip;
        MenuSource.Play();
    }
}
