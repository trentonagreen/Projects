using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public Transform transformDrone;
    void Awake()
    {
        transformDrone = GameObject.FindGameObjectWithTag("Player").transform;
    }

    public Vector3 velocityCameraFollow;
    public Vector3 behindPosition = new Vector3(0, 4, -7);
    public float angle = 15f;
    void FixedUpdate()
    {
        transform.position = Vector3.SmoothDamp(transform.position, transformDrone.transform.TransformPoint(behindPosition) + Vector3.up * Input.GetAxis("Vertical"), ref velocityCameraFollow, 0.1f);
        //transform.rotation = Quaternion.Euler(new Vector3(angle, transformDrone.GetComponent<FlyMovement>().currRotationY, 0));
        transform.rotation = Quaternion.Euler(new Vector3(angle, transformDrone.GetComponent<FlyMovement>().currRotationY, 0));
    }
}
