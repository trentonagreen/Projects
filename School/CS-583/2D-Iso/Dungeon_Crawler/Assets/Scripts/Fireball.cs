using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Fireball : MonoBehaviour
{
    [SerializeField]
    bool x;
    [SerializeField]
    bool y;
    [SerializeField]
    bool z;

    Vector3 localPosition0;

    // Start is called before the first frame update
    void Awake()
    {
        SetOriginalLocalPosition();
        Destroy(gameObject, 5);
    }

    // Update is called once per frame
    void Update()
    {
        float x, y, z;

        if (this.x)
            x = localPosition0.x;
        else
            x = transform.localPosition.x;

        if (this.y)
            y = localPosition0.y;
        else
            y = transform.localPosition.y;

        if (this.z)
            z = localPosition0.z;
        else
            z = transform.localPosition.z;


        transform.localPosition = new Vector3(x, y, z);
    }

    public void SetOriginalLocalPosition()
    {
        localPosition0 = transform.localPosition;
    }

}
