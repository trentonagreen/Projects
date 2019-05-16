using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BetterPickUp : MonoBehaviour
{
    RaycastHit hit;
    Ray r;
    Rigidbody ballRB;
    Vector3 ballScale;
    Vector3 objPos;
    Camera playerCamera;
    GameObject ballPos;
    TrailRenderer trail;

    GameObject throwAngle;

    public bool isThrown = false;
    public bool isHolding = false;
    public bool isDestroyed = false;
    public bool canBeHeld = true;
    public int ballsThrown;

    FPS_Controller playerCS;
    BallSpawner spawnerCS;

    void Start()
    {
        ballRB = this.GetComponent<Rigidbody>();
        ballScale = this.transform.localScale;

        playerCamera = Camera.main;

        ballPos = GameObject.FindWithTag("PickUpPos");
        throwAngle = GameObject.FindWithTag("ThrowAngle");

        playerCS = GameObject.FindWithTag("Player").GetComponent<FPS_Controller>();
        spawnerCS = GameObject.FindWithTag("Spawner").GetComponent<BallSpawner>();

        trail = this.GetComponent<TrailRenderer>();
        trail.enabled = false;

        canBeHeld = true;
    }

    void Update()
    {
        r = new Ray(playerCamera.transform.position, playerCamera.transform.forward);

        this.transform.localScale = ballScale;

        if(Physics.Raycast(r, out hit))
        {
            if(hit.transform.CompareTag("Ball") && canBeHeld == true)
            {
                if(Input.GetKeyDown(KeyCode.E))
                {
                    isHolding = true;
                    canBeHeld = false;
                    ballRB.useGravity = false;
                    ballRB.detectCollisions = false; ;
                }
            }
        }

        if(isHolding)
        {
            ballRB.velocity = Vector3.zero;
            ballRB.angularVelocity = Vector3.zero;
            this.transform.SetParent(ballPos.transform);

            this.transform.localPosition = Vector3.zero;
            this.transform.localRotation = Quaternion.identity;
        }
        else
        {
            objPos = this.transform.position;
            this.transform.SetParent(null);
            ballRB.useGravity = true;
            ballRB.detectCollisions = true;
            this.transform.position = objPos;
        }
    }

    private void FixedUpdate()
    {
        if(isHolding)
        {
            if(Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0))
            {
                trail.enabled = true;

                ballRB.useGravity = true;
                isHolding = false;
                isThrown = true;
                //ballRB.AddForce(playerCamera.transform.forward * playerCS.throwForce);
                ballRB.AddForce(throwAngle.transform.forward * playerCS.throwForce);
                playerCS.ballsThrown++;

                Destroy(gameObject, 4f);
            }
        }
    }

    private void OnDestroy()
    {
        Debug.Log("Ball was destroyed");
        spawnerCS.canSpawn = true;
    }
}
