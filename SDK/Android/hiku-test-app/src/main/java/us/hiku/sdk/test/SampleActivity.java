package us.hiku.sdk.test;

import android.app.Activity;
import android.content.SharedPreferences;
import android.support.v4.app.NavUtils;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.widget.TextView;

import us.hiku.android.sdk.HikuSetupSDK;


public class SampleActivity extends Activity {

    HikuSetupSDK mSdk;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sample);
        getActionBar().setDisplayHomeAsUpEnabled(true);

        mSdk = HikuSetupSDK.getInstance(this);

        TextView email = (TextView) findViewById(R.id.email);
        email.setText(mSdk.getEmail());

        TextView token = (TextView) findViewById(R.id.token);
        token.setText(mSdk.getAuthorizationToken());

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
//        getMenuInflater().inflate(R.menu.menu_sample, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        } else if (id == android.R.id.home) {
            NavUtils.navigateUpFromSameTask(this);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
