using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tower : MonoBehaviour
{
    public Transform fireBallSpawnN;
    public Transform fireBallSpawnS;
    public Transform fireBallSpawnE;
    //public Transform fireBallSpawnW;

    public GameObject fireBallPrefab;

    public DC_Character_Controller playerController;

    bool flag = true;

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(Spawn());
    }

    private void Update()
    {
        if(playerController.hasGem == true)
        {
            flag = false;
        }
    }

    public IEnumerator Spawn()
    {
        while (flag)
        {
            GameObject fireballN = Instantiate(fireBallPrefab, fireBallSpawnN.position, Quaternion.identity);
            GameObject fireballS = Instantiate(fireBallPrefab, fireBallSpawnS.position, Quaternion.identity);
            GameObject fireballE = Instantiate(fireBallPrefab, fireBallSpawnE.position, Quaternion.identity);
            //GameObject fireballW = Instantiate(fireBallPrefab, fireBallSpawnW.position, Quaternion.identity);

            Rigidbody fireNrb = fireballN.GetComponent<Rigidbody>();
            Rigidbody fireSrb = fireballS.GetComponent<Rigidbody>();
            Rigidbody fireErb = fireballE.GetComponent<Rigidbody>();
            //Rigidbody fireWrb = fireballW.GetComponent<Rigidbody>();

            fireNrb.velocity = fireBallSpawnN.forward * 2;
            fireSrb.velocity = fireBallSpawnS.forward * 2;
            fireErb.velocity = fireBallSpawnE.forward * 2;
            //fireWrb.velocity = fireBallSpawnW.forward * 2;

            yield return new WaitForSeconds(5f);
        }
    }
}
