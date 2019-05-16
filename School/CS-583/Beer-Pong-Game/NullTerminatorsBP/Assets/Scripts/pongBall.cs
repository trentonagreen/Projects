using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class pongBall : MonoBehaviour
{
    public AudioSource bloopSource;

    // Start is called before the first frame update
    void Start()
    {
        bloopSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag == "Red Solo Cup Variant") {
            bloopSource.Play();

            Destroy(collision.gameObject);
        }
    }
}
