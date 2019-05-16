using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BallsCounter : MonoBehaviour {

    Text text;

    FPS_Controller playerCS;

    private void Start()
    {
        playerCS = GameObject.FindWithTag("Player").GetComponent<FPS_Controller>();
    }

    void Awake() {
        text = GetComponent<Text>();
    }

    // Update is called once per frame
    void Update() {
        text.text = "BALLS: " + (BallSpawner.MAX_BALLS - playerCS.ballsThrown);
    }
}
