using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeepOriginalPos : MonoBehaviour
{
    public Vector3 orignalTransUp;
    Quaternion orignalRotation;

    // Start is called before the first frame update
    void Start()
    {
        orignalRotation = transform.rotation;
        orignalTransUp = transform.up;
    }

    // Update is called once per frame
    void Update()
    {
        transform.rotation = orignalRotation;

    }
}
