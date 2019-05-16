using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThrowBall : MonoBehaviour
{
    public GameObject ball;
    public GameObject playerCam;

    public float ballDistance = 2f;         // distance from player's 'face'
    public float ballThrowForce = 100f;     // throwing power of ball

    public bool holdingBall = false;

    // Start is called before the first frame update
    void Start()
    {
        ball.GetComponent<Rigidbody>().useGravity = false;
    }

    // Update is called once per frame
    void Update()
    { 
        if(holdingBall)
        {
            ball.transform.position = playerCam.transform.position + playerCam.transform.forward * ballDistance;

            if (Input.GetKey(KeyCode.Space))
            {
                holdingBall = false;
                ball.GetComponent<Rigidbody>().useGravity = true;
                ball.GetComponent<Rigidbody>().AddForce(playerCam.transform.forward * ballThrowForce);
            }
        }

        if(Input.GetKey(KeyCode.E))
        {
            holdingBall = true;
            ball.GetComponent<Rigidbody>().velocity = Vector3.zero;
            ball.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
        }
    }
}
