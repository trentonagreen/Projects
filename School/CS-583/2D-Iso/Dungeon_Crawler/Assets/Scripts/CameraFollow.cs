using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public Transform playerTarget;
    public Vector3 offset;

    private void LateUpdate()
    {
        transform.position = playerTarget.position + offset;
    }
}
