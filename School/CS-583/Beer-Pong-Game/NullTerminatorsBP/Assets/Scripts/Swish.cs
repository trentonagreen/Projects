using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Swish : MonoBehaviour
{
    public ParticleSystem splash;
    public GameObject cupParent;
    public AudioSource bloopSource;

    private void Start()
    {
        bloopSource = GetComponent<AudioSource>();
    }

    private void OnCollisionEnter( Collision collision ) {
        if (collision.gameObject.CompareTag("Ball")) {
            collision.gameObject.SetActive(false);
            ScoreManager.score++;
            splash.Play();
            bloopSource.Play();
            Destroy(cupParent, 4f);
            // if( BallSpawner.MAX_BALLS - BallSpawner.ballsThrown == 0 ) SceneManager.LoadScene( 0 );
        }
    }

}
