using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallSpawner : MonoBehaviour
{
    FPS_Controller playerCS;

    public static int ballsThrown;  // static
    public GameObject ballPrefab;
    public bool canSpawn = false;

    public static int MAX_BALLS = 10;   //static

    // Start is called before the first frame update
    void Start()
    {
        ballsThrown = 0;

        GameObject startBall = Instantiate(ballPrefab, this.transform.position, Quaternion.identity);

        playerCS = GameObject.FindWithTag("Player").GetComponent<FPS_Controller>();
        canSpawn = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(playerCS.ballsThrown > ballsThrown && playerCS.ballsThrown < MAX_BALLS && canSpawn == true)
        {
            // create ball
            Debug.Log("Creating Ball");

            ballsThrown++;

            GameObject newBall = Instantiate(ballPrefab, this.transform.position, Quaternion.identity);
            canSpawn = false;
        }

        if(ballsThrown == MAX_BALLS)
        {
            Debug.Log("You ran out of balls to throw");
        }
    }
}
