//
//  ViewController.swift
//  iOT-light-bulb
//
//  Created by Johnson Lai on 13/05/2017.
//  Copyright © 2017 johnsonlwh7. All rights reserved.
//

import UIKit
import AVFoundation

class ViewController: UIViewController {
    var websiteUrl = "http://192.168.0.15"
    var btnSound: AVAudioPlayer!
    override func viewDidLoad() {
        super.viewDidLoad()
        let path = Bundle.main.path(forResource: "btn", ofType: "wav")
        let soundURL = URL(fileURLWithPath: path!)
        do {
            try btnSound = AVAudioPlayer(contentsOf: soundURL)
            btnSound.prepareToPlay()
        } catch let err as NSError {
            print(err.debugDescription)
        }

        
    }
    @IBAction func onBtnPressed(_ sender: Any) {
        playSound()
        let url = URL(string: "\(websiteUrl)/LED=ON")
        
        let onTask = URLSession.shared.dataTask(with: url!) {
            (data, response, error) in
            let html = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)!
            print(html)
        }
        onTask.resume()
    }
    @IBAction func offBtnPressed(_ sender: Any) {
        playSound()
        let url = URL(string: "\(websiteUrl)/LED=OFF")
        
        let offTask = URLSession.shared.dataTask(with: url!) {
            (data, response, error) in
            let html = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)!
            print(html)
        }
        
        offTask.resume()
    }
    func playSound() {
        if btnSound.isPlaying {
            btnSound.stop()
        }
        
        btnSound.play()
    }
}

