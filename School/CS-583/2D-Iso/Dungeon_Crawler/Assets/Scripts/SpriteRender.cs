using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpriteRender : MonoBehaviour
{

    Quaternion initRot;

    // Start is called before the first frame update
    void Start()
    {
        initRot = transform.rotation;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        transform.rotation = initRot;
    }

}
