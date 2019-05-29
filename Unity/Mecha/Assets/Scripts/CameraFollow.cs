using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public Transform transformDrone;

    public float mouseSensitivity = 10f;
    public Transform target;
    public float distFromTarget = 2f;
    public Vector2 pitchRange = new Vector2(-25, 85);

    public float rotSmoothTime = .1f;
    Vector3 rotSmoothVel;
    Vector3 currRot;

    private float yaw;
    private float pitch;

    void Awake()
    {
        transformDrone = GameObject.FindGameObjectWithTag("Player").transform;
    }

    public Vector3 velocityCameraFollow;
    public Vector3 behindPosition = new Vector3(0, 4, -7);
    public float angle = 15f;
    void FixedUpdate()
    {
        //transform.position = Vector3.SmoothDamp(transform.position, transformDrone.transform.TransformPoint(behindPosition) + Vector3.up * Input.GetAxis("Vertical"), ref velocityCameraFollow, 0.1f);
        //transform.rotation = Quaternion.Euler(new Vector3(angle, transformDrone.GetComponent<FlyMovement>().currRotationY, 0));
        //transform.rotation = Quaternion.Euler(new Vector3(angle, transformDrone.GetComponent<FlyMovement>().currRotationY, 0));
    }

    void LateUpdate()
    {
        yaw += Input.GetAxis("Mouse X") * mouseSensitivity;
        pitch -= Input.GetAxis("Mouse Y") * mouseSensitivity;
        pitch = Mathf.Clamp(pitch, pitchRange.x, pitchRange.y);

        currRot = Vector3.SmoothDamp(currRot, new Vector3(pitch, yaw), ref rotSmoothVel, rotSmoothTime);
        transform.eulerAngles = currRot;

        transform.position = target.position - transform.forward * distFromTarget;
    }
}
